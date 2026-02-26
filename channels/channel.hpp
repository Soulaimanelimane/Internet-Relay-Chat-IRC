/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:37:16 by slimane           #+#    #+#             */
/*   Updated: 2026/02/26 12:07:12 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "../clients/client.hpp"

// class Client;

class Channel
{
	private:
		std::string             name;
		std::string             topic;
		std::vector<Client *>   members;
		std::vector<Client *>   ops;
		std::vector<Client *>   invited;
		bool                    invite_only;
		bool                    tp_rest;
		std::string             password;
		size_t                  curr_member;
		size_t                  lim_membrs;
		size_t                  def_lim_members;

	public:
		Channel(Client &cls, std::string &channel_name);
		~Channel();

        std::string getname();
        void add_member(Client &cls);
        std::vector<Client*> &getmembers();
        void remove_member(Client &cls, Client &rmvr);
        void remove_operator(Client &cls, Client &rmvr);
        void invite_member(Client &host, Client &guest);
        void ft_topic(Client &cls, std::string &topic);
        void ft_topic(Client &cls);
        void ft_mode(Client &cls , std::string &md);
        void add_member_to_operator(Client &cls, Client &oprtr);
        void ft_broadcast(Client &sender, std::string &msg);
        void ft_broadcast_all(std::string &msg);
        bool isUserInChannel(const std::string &nickname) const;
        std::vector<Client*> &get_ops();
		int     check_is_in(Client &rmvr, std::vector<Client *> list);
		void    remove_itself(Client &cls);
		std::string &get_name();

        std::vector<std::string>   signmodes;

};

#endif